import subprocess
import urllib2
import re
import os
from os.path import expanduser


def parse_diff(diff_url):
    diff = urllib2.urlopen(diff_url).read()
    # print diff
    diff_list = [match[13:].split(" ")[0] for match in re.findall(r'diff --git .*', diff)]
    return diff_list
    # print diff


def download_all_the_shit(d_url, br_name):
    f_name = '#'.join(d_url.split('/')[-4:])
    diff_files = parse_diff(d_url)
    print diff_files
    full_folder_name = expanduser("~") + "/pull_requests/" + f_name
    # https://github.com/LogvinovLeon/Github_Code_Style/blob/br2/server/YouCheck/4
    for _file in diff_files:
        my_path_file = full_folder_name + "/" + _file
        temp = d_url.split('/')[3:5]
        temp.extend([br_name, _file])
        fi_url = "https://raw.githubusercontent.com/" + '/'.join(temp)
        print fi_url
        if not os.path.exists(os.path.dirname(my_path_file)):
            if os.path.dirname(my_path_file):
                os.makedirs(os.path.dirname(my_path_file))
        with open(my_path_file, "w") as text_file:
            print my_path_file
            try:
                text_file.write(urllib2.urlopen(fi_url).read())
            except:
                pass
    return full_folder_name


cerr = """[/home/leonid/pull_requests/LogvinovLeon#Github_Code_Style#pull#5.diff/ms332521+ab346870/private/monety.cpp:76]: (style) Unused variable: interval_start_iterator
[/home/leonid/pull_requests/LogvinovLeon#Github_Code_Style#pull#5.diff/ms332521+ab346870/private/monety.cpp:77]: (style) Unused variable: interval_end_interator
[/home/leonid/pull_requests/LogvinovLeon#Github_Code_Style#pull#5.diff/ms332521+ab346870/private/monety.cpp:86]: (performance) Prefer prefix ++/-- operators for non-primitive types.
[/home/leonid/pull_requests/LogvinovLeon#Github_Code_Style#pull#5.diff/ms332521+ab346870/private/ostateczny_plik_i_testy/monety.cc:90]: (performance) Prefer prefix ++/-- operators for non-primitive types.
[/home/leonid/pull_requests/LogvinovLeon#Github_Code_Style#pull#5.diff/ms332521+ab346870/private/ostateczny_plik_i_testy/monety.cc:112]: (performance) Prefer prefix ++/-- operators for non-primitive types.
[/home/leonid/pull_requests/LogvinovLeon#Github_Code_Style#pull#5.diff/ms332521+ab346870/private/ostateczny_plik_i_testy/monety.cc:118]: (performance) Prefer prefix ++/-- operators for non-primitive types.
[/home/leonid/pull_requests/LogvinovLeon#Github_Code_Style#pull#5.diff/ms332521+ab346870/private/ostateczny_plik_i_testy/monety.cc:124]: (performance) Prefer prefix ++/-- operators for non-primitive types.
[/home/leonid/pull_requests/LogvinovLeon#Github_Code_Style#pull#5.diff/ms332521+ab346870/private/ostateczny_plik_i_testy/monety.cc:128]: (performance) Prefer prefix ++/-- operators for non-primitive types.
[/home/leonid/pull_requests/LogvinovLeon#Github_Code_Style#pull#5.diff/ms332521+ab346870/private/ostateczny_plik_i_testy/monety.cc:134]: (performance) Prefer prefix ++/-- operators for non-primitive types.
[/home/leonid/pull_requests/LogvinovLeon#Github_Code_Style#pull#5.diff/ms332521+ab346870/private/read_lines.cpp:20]: (style) Variable 'year' is allocated memory that is never used.
[/home/leonid/pull_requests/LogvinovLeon#Github_Code_Style#pull#5.diff/ms332521+ab346870/private/read_lines.cpp:23]: (style) Unused variable: a
[/home/leonid/pull_requests/LogvinovLeon#Github_Code_Style#pull#5.diff/ms332521+ab346870/private/read_lines.cpp:23]: (style) Unused variable: b
[/home/leonid/pull_requests/LogvinovLeon#Github_Code_Style#pull#5.diff/ms332521+ab346870/private/read_lines.cpp:52]: (error) Memory leak: match
[/home/leonid/pull_requests/LogvinovLeon#Github_Code_Style#pull#5.diff/ms332521+ab346870/private/read_lines.cpp:52]: (error) Memory leak: year
[/home/leonid/pull_requests/LogvinovLeon#Github_Code_Style#pull#5.diff/ms332521+ab346870/private/read_lines2.cpp:101]: (style) Unused variable: lines
[/home/leonid/pull_requests/LogvinovLeon#Github_Code_Style#pull#5.diff/ms332521+ab346870/private/read_lines2.cpp:102]: (style) Variable 'line_num' is assigned a value that is never used.
[/home/leonid/pull_requests/LogvinovLeon#Github_Code_Style#pull#5.diff/ms332521+ab346870/private/read_lines2.cpp:103]: (warning) Redundant code: Found a statement that begins with numeric constant.
(information) Cppcheck cannot find all the include files (use --check-config for details)
"""


def cpp_check(full_folder_name):
    print full_folder_name

    process = subprocess.Popen(
        ["/home/leonid/cppcheck", "--enable=all", "--inconclusive", "--std=posix", full_folder_name + "/*"],
        stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    process.wait()
    (_, err) = process.communicate()

    for line in err.split("\n"):
        print line


diff_url = "https://github.com/LogvinovLeon/Github_Code_Style/pull/5.diff"
full_folder_name = download_all_the_shit(diff_url, "cpp-br")
cpp_check(full_folder_name)
