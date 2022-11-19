from django.contrib import admin

from .models import Task


@admin.action(description='Delete assignee')
def delete_assignee(modeladmin, request, queryset):
    queryset.update(assignee=None)


@admin.register(Task)
class TaskAdmin(admin.ModelAdmin):
    list_display = ('title', 'description', 'assignee')
    actions = [delete_assignee]
