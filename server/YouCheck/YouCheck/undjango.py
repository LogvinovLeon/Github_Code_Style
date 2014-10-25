import urllib2
import re
import os

def parse_diff(diff_url):
    diff = urllib2.urlopen(diff_url).read()
    return [match[13:].split(" ")[0] for match in re.findall('diff --git.*', diff)]
    #print diff

def download_all_the_shit(d_url):
    f_name = '#'.join(d_url.split('/')[-4:])
    os.makedirs(f_name)
    diff_files = parse_diff(d_url)
    #https://github.com/LogvinovLeon/Github_Code_Style/blob/br2/server/YouCheck/4
    for file in diff_files:


download_all_the_shit("https://github.com/LogvinovLeon/Github_Code_Style/pull/2.diff")

