from django.http import HttpResponse

from django.views.decorators.csrf import csrf_exempt
import json
import urllib2

@csrf_exempt
def get_post(request):
    json_data = json.loads(request.body)
    diff_url = json.dumps(json_data['pull_request']['diff_url'], sort_keys=True, indent=4 * ' ')
    # "https://github.com/LogvinovLeon/Github_Code_Style/pull/2.diff"
    return HttpResponse(request)