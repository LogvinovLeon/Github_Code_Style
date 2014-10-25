from django.http import HttpResponse

from django.views.decorators.csrf import csrf_exempt
import json
@csrf_exempt
def get_post(request):
	json_data = json.loads(request.body)
	print(json.dumps(json_data['pull_request']['diff_url'], sort_keys=True, indent=4 * ' '))
	return HttpResponse(request);
