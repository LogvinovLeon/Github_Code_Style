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
    diff_files.extend(['.astylerc'])
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
    print "astyle_check"
    process = subprocess.Popen(
        ['./run_astyle.sh', full_folder_name + '/'],
        stderr=subprocess.PIPE)
    process.wait()
    (_, err) = process.communicate()

    files = []

    lines = err.split('\n')

    print "len(lines) = " + str(len(lines))

    current_file = None
    current_interval = None

    for line in lines:
        print "line=" + line
        header = re.search('^(?P<lines_new>\d+(,\d+)?)c(?P<lines_old>\d+(,\d+)?)', line)
        old_line = re.search('<(?P<old_line>.*)', line)
        new_line = re.search('>(?P<new_line>.*)', line)
        filename_re = re.search('filename=(?P<filename>.*)', line)
        print "search completed"
        if header is not None:
            begin=0
            end=0

            lines_old = header.group('lines_old').split(',')
            if len(lines_old) == 1:
                begin = int(lines_old[0])
                end = begin
            else:
                begin = int(lines_old[0])
                end = int(lines_old[1])

            print "begin=" + str(begin) + ", end=" + str(end)

            if current_interval is not None:
                current_file['notifications'].append(current_interval)

            current_interval = {
                'lines': {
                    'begin': begin,
                    'end': end,
                },
                'content': '',
                'type': ['formatting']
            }
        elif old_line is not None:
            print "this is old line, ignoring"
        elif new_line is not None:
            nl = new_line.group('new_line')
            print "new_line=" + nl
            current_interval['content'] += nl + '\n'
        elif filename_re is not None:
            print "this is filename"
            filename = filename_re.group('filename')

            if current_interval is not None:
                current_file['notifications'].append(current_interval)

            if current_file is not None:
                files.append(current_file)

            current_file = {
                'filename': filename[2:],
                'notifications': [],
            }

            current_interval = None

            print filename

    # print 'files='
    print files

    return files

def parse_cppcheck_result(res, full_folder_name):
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
                noti = {
                    "type": types,
                    "content": desc,
                    "lines": {
                        "begin": ln,
                        "end": ln,
                    }
                }
                if _file in ddict:
                    ddict[_file].extend([noti])
                else:
                    ddict[_file] = [noti]
    tab = [{"filename": key, "notifications": value} for key, value in
           ddict.iteritems()]
    # return tab
    return ddict
    #return {"pull": id, "files": tab}


def get_pull_request_id(diff_url):
    return diff_url.split("/")[-1:][0].split('.')[0]

