import subprocess
import urllib2
import re
import os
from os.path import expanduser
import json


def parse_diff(diff_url):
    diff = urllib2.urlopen(diff_url).read()
    diff_list = [match[13:].split(" ")[0] for match in
                 re.findall(r'diff --git .*', diff)]
    return diff_list


def download_all_the_shit(d_url, br_name):
    f_name = '#'.join(d_url.split('/')[-4:])
    diff_files = parse_diff(d_url)
    full_folder_name = expanduser("~") + "/pull_requests/" + f_name
    for _file in diff_files:
        my_path_file = full_folder_name + "/" + _file
        temp = d_url.split('/')[3:5]
        temp.extend([br_name, _file])
        fi_url = "https://raw.githubusercontent.com/" + '/'.join(temp)
        if not os.path.exists(os.path.dirname(my_path_file)):
            if os.path.dirname(my_path_file):
                os.makedirs(os.path.dirname(my_path_file))
        with open(my_path_file, "w") as text_file:
            try:
                text_file.write(urllib2.urlopen(fi_url).read())
            except:
                pass
    return full_folder_name


def cpp_check(full_folder_name):
    process = subprocess.Popen(
        [expanduser("~") + "/cppcheck", "--enable=all", "--inconclusive",
         "--std=posix", full_folder_name + "/*"],
        stderr=subprocess.PIPE)
    process.wait()
    (_, err) = process.communicate()
    return err.split("\n")

def astyle_check(full_folder_name):
    process = subprocess.Popen(
        ['./run_astyle.sh', full_folder_name + '/'],
        stderr=subprocess.PIPE)
    process.wait()
    (_, err) = process.communicate()
    print err
    return err.split('\n')
    )

def parse_cppcheck_result(res, id, full_folder_name):
    ddict = {}
    for line in res:
        if len(line) > 0:
            if line[0:len(full_folder_name) + 1] == "[" + full_folder_name:
                nline = line[len(full_folder_name) + 2:]
                phrases = nline.split(":", 2)
                (_file, ln, tmp) = (
                phrases[0], phrases[1][:-1], phrases[2][1:])
                desc = tmp.split(") ", 1)
                types = desc[0][1:].split(", ")
                desc = desc[1]
                noti = {"type": types, "content": desc, "line": ln}
                if _file in ddict:
                    ddict[_file].extend([noti])
                else:
                    ddict[_file] = [noti]
    tab = [{"filename": key, "notifications": value} for key, value in
           ddict.iteritems()]
    return {"pull": id, "files": tab}


def get_pull_request_id(diff_url):
    return diff_url.split("/")[-1:][0].split('.')[0]

