from django.db import models

# Create your models here.
from developer.models import Developer


class Task(models.Model):
    title = models.CharField(max_length=100, unique=True)
    description = models.TextField()
    assignee = models.ForeignKey(
        Developer,
        related_name="tasks",
        on_delete=models.CASCADE,
        null=True,
        blank=True,
        verbose_name="assignee"
    )

    def __str__(self):
        return f"{self.title} ({self.description}) ({self.assignee})"


