from django.views.generic import base
class ServerScoresView(base):
    def get(self, request):
        print request
