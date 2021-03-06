from django.http import HttpResponse, Http404

from django.views.decorators.csrf import csrf_exempt
import json
import urllib2
from undjango import *


@csrf_exempt
def get_post(request):
    json_data = json.loads(request.body)
    diff_url = json.dumps(json_data['pull_request']['diff_url'])[1:-1]
    branch_name = json.dumps(json_data['pull_request']['head']['ref'])[1:-1]
    pull_request_id = get_pull_request_id(diff_url)
    full_folder_name = download_all_the_shit(diff_url, branch_name)
    res = cpp_check(full_folder_name)
    with open(full_folder_name + "/result.json", "w") as text_file:
        # try:
        #pull_request_id
        ccheck = parse_cppcheck_result(res, full_folder_name)
        formatting = astyle_check(full_folder_name)
        dict = ccheck

        print "FORMATTING###"
        print formatting

        print "CCHECK###"
        print ccheck

        print "END###"

        for x in formatting:
            filename = x['filename']
            notifs = x['notifications']
            print "FILENAME### " + filename
            print "notifs="
            print notifs

            print "dict[filename]="

            if filename in dict:
                dict[filename].extend(notifs)
            else: dict[filename] = notifs

        merged = [
            {
                'filename': key,
                'notifications': value
            } for key, value in dict.iteritems()
        ]
        # merged = dict

        result = {"pull": pull_request_id, "files": merged}
        text_file.write(json.dumps(result, indent=2))

    with open(full_folder_name + "/formatting.json", "w") as formatting_file:
        formatting_file.write(json.dumps(astyle_check(full_folder_name), indent=2))

    return HttpResponse(request)

@csrf_exempt
def client(request, user_name, repo_name, pull_id):
    file_name = os.path.join(expanduser("~"),
                             "pull_requests", '#'.join([user_name, repo_name, "pull", pull_id + ".diff"]),
                             "result.json")
    print file_name
    if os.path.exists(file_name):
	with open(file_name, "r") as _file:
            content = _file.read()
	    print content
	    return HttpResponse(content, mimetype='application/json')
    return HttpResponse(status=102)

@csrf_exempt
def format(request, user_name, repo_name, pull_id):
    file_name = os.path.join(expanduser("~"),
                             "pull_requests", '#'.join([user_name, repo_name, "pull", pull_id + ".diff"]),
                             "formatting.json")
    print file_name
    if os.path.exists(file_name):
	with open(file_name, "r") as _file:
            content = _file.read()
	    print content
	    return HttpResponse(content, mimetype='application/json')
    return HttpResponse(status=102)