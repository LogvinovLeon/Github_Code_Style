from django.conf.urls import patterns, include, url
from YouCheck import views
# Uncomment the next two lines to enable the admin:
# from django.contrib import admin
# admin.autodiscover()

urlpatterns = patterns('',
    url(r'^$', views.get_post),
    url(r'^client/(?P<user_name>\w+)/(?P<repo_name>\w+)/(?P<pull_id>\d+)$', views.client),
)
