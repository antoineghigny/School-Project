<!doctype html>
<html lang="fr">
<head>
    <meta charset="UTF-8">
    <meta name="csrf-token" content="{{ csrf_token() }}">
    <meta name="viewport"
          content="width=device-width, user-scalable=no, initial-scale=1.0, maximum-scale=1.0, minimum-scale=1.0">
    <meta http-equiv="X-UA-Compatible" content="ie=edge">
    <title>Students CRUD</title>
    <link rel="stylesheet" href="{{ asset('css/popup.css') }}">
</head>
<body>

<div class="container">
    <table id="studentsTable">
        <thead>
        <tr>
            <th>Id</th>
            <th>Prénom</th>
            <th>Nom</th>
            <th>Groupe</th>
            <th>Mettre à jour</th>
            <th>Suppression</th>
        </tr>
        </thead>
        <tbody>
        @foreach($students as $student)
            <tr>
                <td class="etuId">{{ $student->id_student }}</td>
                <td>{{ $student->firstname }}</td>
                <td>{{ $student->lastname }}</td>
                <td>{{ $student->group }}</td>
                <td>
                    <button onclick="displayPopup({{$student->id_student}}, '{{$student->firstname}}',
                        '{{$student->lastname}}', '{{$student->group}}')">Update</button>
                </td>
                <td><form id="formDelete" method="POST" action="{{route('student.delete')}}">
                        @csrf
                        <input name="id" type="hidden" value="{{$student->id_student}}">
                        <input name="" type="submit" value="Supprimer">
                    </form>
                </td>
            </tr>
        @endforeach
        </tbody>
    </table>

    <button onclick="displayForm()">Ajouter un étudiant</button>

    <form id="formulaire" method="POST" action="{{ route('student.store') }}">
        @csrf
        <div>
            <label for="firstname">Prénom</label>
            <input type="text" id="firstname" name="firstname" placeholder="Prénom">
        </div>
        <div>
            <label for="lastname">Nom</label>
            <input type="text" id="lastname" name="lastname" placeholder="Nom">
        </div>
        <div>
            <label for="group">Groupe</label>
            <input type="text" id="group" name="group" placeholder="Groupe">
        </div>
        <div>
            <label for="id_student">Id</label>
            <input type="number" id="id_student" name="id_student" placeholder="Id de l'étudiant">
        </div>
        <button type="submit" value="Envoyer">Ajouter</button>
    </form>
</div>

<div class="popupZbi">
    <div class="popupcontent">
        <h1 id="titlePopup">Test</h1>
        <form id="formulaire" method="POST" action="{{ route('student.edit') }}">
            @csrf
            <div>
                <label for="firstname">Prénom</label>
                <input type="text" id="firstnamePopup" name="firstname" placeholder="Prénom">
            </div>
            <div>
                <label for="lastname">Nom</label>
                <input type="text" id="lastnamePopup" name="lastname" placeholder="Nom">
            </div>
            <div>
                <label for="group">Groupe</label>
                <input type="text" id="groupPopup" name="group" placeholder="Groupe">
            </div>
            <div>
                <label for="id_student">Id</label>
                <input type="number" id="id_studentPopup" name="id_student" placeholder="Id de l'étudiant">
            </div>
            <button type="submit" value="Envoyer">Update</button>
        </form>
        <button onclick="closePopup()">Fermer</button>
    </div>
</div>

<script>

    document.addEventListener("DOMContentLoaded", function(event) {
        document.getElementById("formulaire").style.display = "none";
        document.getElementsByClassName("popupZbi")[0].style.display = "none";
    });

    function deleteStudent(id) {
        console.log(id)
        let token = document.querySelector("meta[name='csrf-token']").getAttribute('content');

        fetch('/api/crudstudent/' + id, {
            method: 'POST',
            headers: {'X-CSRF-TOKEN': token,}
        }).then(response => {
            console.log(response)
            if (response.status === 200) {
                window.location.reload()
            }
        })
    }

    function displayForm(){
        document.getElementById("formulaire").style.display = "block";
    }

    function displayPopup(id, firstname, lastname, group){
        document.getElementsByClassName("popupZbi")[0].style.display = "block";
        console.log(id, firstname, lastname, group);
        document.getElementById("id_studentPopup").value = id;
        document.getElementById("firstnamePopup").value = firstname;
        document.getElementById("lastnamePopup").value = lastname;
        document.getElementById("groupPopup").value = group;
        document.getElementById("titlePopup").textContent = "Modification de l'étudiant : " + id
    }

    function closePopup(){
        document.getElementsByClassName("popupZbi")[0].style.display = "none";
    }

</script>

</body>
</html>
