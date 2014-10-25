import subprocess
import urllib2
import re
import os
from os.path import expanduser


def parse_diff(diff_url):
    diff = urllib2.urlopen(diff_url).read()
    return [match[13:].split(" ")[0] for match in re.findall('diff --git.*', diff)]
    # print diff


def download_all_the_shit(d_url, br_name):
    f_name = '#'.join(d_url.split('/')[-4:])
    try:
        os.makedirs(f_name)
    except OSError as exception:
        pass
    diff_files = parse_diff(d_url)
    full_folder_name = expanduser("~") + "/pull_requests/" + f_name
    # https://github.com/LogvinovLeon/Github_Code_Style/blob/br2/server/YouCheck/4
    for _file in diff_files:

        my_path_file = full_folder_name + "/" + _file
        temp = d_url.split('/')[3:5]
        temp.extend([br_name, _file])
        fi_url = "https://raw.githubusercontent.com/" + '/'.join(temp)
        #print fi_url
        if not os.path.exists(os.path.dirname(my_path_file)):
            if os.path.dirname(my_path_file):
                os.makedirs(os.path.dirname(my_path_file))
        with open(my_path_file, "w") as text_file:
            #print my_path_file
            text_file.write(urllib2.urlopen(fi_url).read())
    return full_folder_name


def cpp_check(full_folder_name):
    print full_folder_name

    process = subprocess.Popen(
        ["/home/leonid/cppcheck", "--enable=all", "--inconclusive", "--std=posix", full_folder_name + "/*"],
        stdout=subprocess.PIPE)
    (output, err) = process.communicate()
    print output
    exit_code = process.wait()


diff_url = "https://github.com/LogvinovLeon/Github_Code_Style/pull/3.diff"
full_folder_name = download_all_the_shit(diff_url, "br_Lukash")
cpp_check(full_folder_name)
