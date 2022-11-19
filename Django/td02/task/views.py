from msilib.schema import ListView
from django.http import HttpResponse, HttpResponseRedirect
from django.shortcuts import render, get_object_or_404
from django.urls import reverse
from django.views.generic import ListView

from developer.models import Developer
from task.models import Task
from task.forms import TaskForm


class IndexView(ListView):
    model = Task
    template_name = "task/index.html"
    context_object_name = 'tasks'

    def get_context_data(self, **kwargs):
        context = super(IndexView, self).get_context_data(**kwargs)
        context['form'] = TaskForm
        context['app'] = "tasks"
        return context


def dropTask(request, task_id):
    get_object_or_404(Task, pk=task_id).delete()
    return HttpResponseRedirect(reverse('tasks:index'))


def create(request):
    form = TaskForm(request.POST)

    if form.is_valid():
        Task.objects.create(
            title=form.cleaned_data['title'],
            description=form.cleaned_data['description'],
            assignee=form.cleaned_data['assignee']
        )
    return HttpResponseRedirect(reverse('tasks:index'))
