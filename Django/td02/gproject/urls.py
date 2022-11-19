
from django.contrib import admin
from django.urls import include, path

urlpatterns = [
    path('developer/', include("developer.urls")),
    path('admin/', admin.site.urls),
    path('tasks/', include("task.urls")),
    path('', include("home.urls")),
]
