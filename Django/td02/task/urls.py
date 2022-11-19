from django.urls import path
from . import views

from .views import IndexView

app_name = 'tasks'
urlpatterns = [
    path('delete/<int:task_id>', views.dropTask, name='delete'),
    path('create', views.create, name='create'),
    path('tasks', IndexView.as_view(), name='index'),
    path('', IndexView.as_view(), name='index'),
]