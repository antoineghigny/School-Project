from django.test import TestCase

from developer.models import Developer
from django.urls import reverse

# Create your tests here.


class DeveloperModelTests(TestCase):

    def setUp(self):
        Developer.objects.create(first_name="Sébastien", last_name="Drobisz")

    def test_is_free_with_no_tasks(self):

        dev = Developer.objects.create(first_name="Sébastien", last_name="Drobisz")
        self.assertIs(dev.is_free(), True)

    def test_is_free_with_one_tasks(self):
        dev = Developer.objects.create(first_name="Sébastien", last_name="Drobisz")
        dev.tasks.create(title="cours Django", description="Faire le cours sur Django")
        self.assertIs(dev.is_free(), False)


class DeveloperIndexViewTests(TestCase):
    def test_no_developers(self):
        """
        If no developers exist, an appropriate message is displayed.
        """
        response = self.client.get(reverse('developer:index'))
        # print(f"response : {response.content}")
        self.assertEquals(response.status_code, 200)
        self.assertContains(response, "Il n'y a aucune dévelopeur enregistré !")
        self.assertQuerysetEqual(response.context['developers'], [])


    def test_one_developer(self):
        dev = Developer.objects.create(first_name="Jonathan",last_name="Lechien")
        response = self.client.get(reverse('developer:index'))
        self.assertEquals(response.status_code, 200)
        self.assertQuerysetEqual(response.context['developers'],[dev])
        self.assertContains(response, dev.first_name)

class DevDetailView(TestCase):
    def test_existing_developer(self):
  
        dev = Developer.objects.create(first_name="Jonathan",last_name="Lechien")
        url = reverse('developer:detail', args=(dev.id,))
        response = self.client.get(url)
        self.assertEquals(response.status_code, 200)
        self.assertEquals(response.context['developer'], dev)
        self.assertContains(response, dev.first_name)
        self.assertContains(response, dev.last_name)
        
    def test_non_existing_developer(self):
        url = reverse('developer:detail', args=(1,))
        response = self.client.get(url)
        self.assertEquals(response.status_code, 404)