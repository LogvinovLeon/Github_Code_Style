from django.http import HttpResponse

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
        try:
            text_file.write(json.dumps(parse_cppcheck_result(res, pull_request_id, full_folder_name), indent=2))
        except:
            pass
    return HttpResponse(request)
