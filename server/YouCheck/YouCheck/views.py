from django.http import HttpResponse, Http404

from django.views.decorators.csrf import csrf_exempt
import json
import urllib2
from undjango import *


@csrf_exempt
def get_post(request):
    json_data = json.loads(request.body)
    diff_url = json.dumps(json_data['pull_request']['diff_url'])
    branch_name = json.dumps(json_data['pull_request']['head']['ref'])
    print diff_url
    print branch_name
    pull_request_id = get_pull_request_id(diff_url)
    print pull_request_id
    full_folder_name = download_all_the_shit(diff_url, branch_name)
    print full_folder_name
    res = cpp_check(full_folder_name)
    print res
    with open(full_folder_name + "/result.json", "w") as text_file:
        try:
            text_file.write(json.dumps(parse_cppcheck_result(res, pull_request_id, full_folder_name), indent=2))
        except:
            pass
    return HttpResponse(request)


@csrf_exempt
def client(request, user_name, repo_name, pull_id):
    file_name = os.path.join(expanduser("~"),
                             "pull_request", '#'.join([user_name, repo_name, pull_id + ".diff"]),
                             "result.json")
    if os.path.exists(file_name):
        with open(file_name, "w") as _file:
            return HttpResponse(_file.read())
    return Http404()