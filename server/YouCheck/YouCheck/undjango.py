import urllib2
import re

def parse_diff(diff_url):
    diff = urllib2.urlopen(diff_url).read()
    print [match[13:].split(" ")[0] for match in re.findall('diff --git.*', diff)]
    #print diff

parse_diff("https://github.com/LogvinovLeon/Github_Code_Style/pull/2.diff")
