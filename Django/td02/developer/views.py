from django.http import HttpResponse, HttpResponseRedirect
from django.shortcuts import render, get_object_or_404
from django.urls import reverse
from django.views.generic import DetailView

from .forms import ShortDeveloperForm
from developer.models import Developer

from django.views.generic import DetailView, ListView


def index(request):
    # return HttpResponse("Hello, world. You're at the developers index.")
    context = {
        'developers': Developer.objects.all(),
        'form': ShortDeveloperForm,
    }
    return render(request, 'developer/index.html', context)


def detail(request, developer_id):
    # developer = Developer.objects.get(pk=developer_id) 👈old
    developer = get_object_or_404(Developer, pk=developer_id)
    return render(request, 'developer/detail.html', {'developer': developer})


def create(request):
    form = ShortDeveloperForm(request.POST)

    if form.is_valid():
        Developer.objects.create(
            first_name=form.cleaned_data['first_name'],
            last_name=form.cleaned_data['last_name'],
            username=form.cleaned_data['username'],
        )

    return HttpResponseRedirect(reverse('developer:index'))


def dropDeveloper(request, developer_id):
    get_object_or_404(Developer, pk=developer_id).delete()
    return HttpResponseRedirect(reverse('developer:index'))


class DevDetailVue(DetailView):
    model = Developer
    template_name = 'developer/detail.html'

    def get_context_data(self, **kwargs):
        context = super().get_context_data(**kwargs)
        context['app'] = "developer"
        return context


class IndexView(ListView):
    model = Developer
    template_name = "developer/index.html"
    context_object_name = 'developers'

    def get_context_data(self, **kwargs):
        context = super(IndexView, self).get_context_data(**kwargs)
        context['form'] = ShortDeveloperForm
        context['app'] = "developer"
        return context
