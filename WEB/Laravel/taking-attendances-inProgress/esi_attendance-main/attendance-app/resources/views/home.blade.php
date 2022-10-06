<!doctype html>
<html lang="fr">
<head>
    <meta charset="UTF-8">
    <meta name="viewport"
          content="width=device-width, user-scalable=no, initial-scale=1.0, maximum-scale=1.0, minimum-scale=1.0">
    <meta http-equiv="X-UA-Compatible" content="ie=edge">
    <meta name="csrf-token" content="{{ csrf_token() }}">
    <title>Document</title>
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.6.0/jquery.min.js"></script>
    <link rel="stylesheet" href="{{ asset('css/output.css') }}">

</head>
<body class="bg-gray-800">
<div class="md:pl-20 md:pr-20 overflow-x-auto lg:pl-48 lg:pr-48">
    <h1 class="m-3 mb-4 text-4xl font-extrabold tracking-tight leading-none text-gray-900 md:text-5xl lg:text-6xl dark:text-white">
        <span class="text-blue-600 dark:text-blue-500">Attendance </span>Table</h1>
    <select name="optionlist"
            class="m-3 inline-flex items-center text-gray-500 bg-white border border-gray-300 focus:outline-none hover:bg-gray-100 focus:ring-4 focus:ring-gray-200 font-medium rounded-lg text-sm px-3 py-1.5 dark:bg-gray-800 dark:text-white dark:border-gray-600 dark:hover:bg-gray-700 dark:hover:border-gray-600 dark:focus:ring-gray-700"
            onChange="">
        <option>All</option>
        <option>E11</option>
        <option>E12</option>
        <option>E13</option>
    </select>

    <table class="w-full text-sm text-left text-gray-500 dark:text-gray-400">
        <thead class="text-xs text-gray-700 uppercase bg-gray-50 dark:bg-gray-700 dark:text-gray-400">
        <tr>
            <th scope="col" class="py-3 px-6">Groupe</th>
            <th scope="col" class="p-4">Id</th>
            <th scope="col" class="py-3 px-6">Prénom</th>
            <th scope="col" class="py-3 px-6">Nom</th>
            <th scope="col" class="p-4">Présences</th>
        </tr>
        </thead>
        <tbody>
        @foreach($students as $student)
            <tr class="bg-white border-b dark:bg-gray-800 dark:border-gray-700 hover:bg-gray-50 dark:hover:bg-gray-600">
                <td class="py-4 px-6 font-medium text-gray-900 whitespace-nowrap dark:text-white">{{ $student->group }}</td>
                <td class="py-4 px-6 font-medium text-gray-900 whitespace-nowrap dark:text-white">{{ $student->id_student }}</td>
                <td class="py-4 px-6 font-medium text-gray-900 whitespace-nowrap dark:text-white">{{ $student->firstname }}</td>
                <td class="py-4 px-6 font-medium text-gray-900 whitespace-nowrap dark:text-white">{{ $student->lastname }}</td>
                <td class="p-4 w-4">
                    <div class="flex items-center">
                        <input type="checkbox" id="{{ $student->id_student }}"
                               class="w-4 h-4 text-blue-600 rounded focus:bg-blue-500 ring-offset-gray-800 focus:ring-2 bg-gray-700 border-gray-600">
                        <label for="checkbox-table-search-1" class="sr-only">checkbox</label>
                    </div>
                </td>
            </tr>
        @endforeach
        </tbody>
        </tfoot>
    </table>
    <div class="m-3 flex space-x-2">
        <button onclick="addAttendance()" type="button"
                class="inline-block px-6 py-3 bg-blue-600 text-white font-medium text-xs leading-tight uppercase rounded shadow-md hover:bg-blue-700 hover:shadow-lg focus:bg-blue-700 focus:shadow-lg focus:outline-none focus:ring-0 active:bg-blue-800 active:shadow-lg transition duration-150 ease-in-out">
            Take presences
        </button>
    </div>

</div>
</body>
<script>


    function convertToJson(nodelist) {
        let obj = [];
        for (let node of nodelist) {
            obj.push({
                'id': node.id,
                'present': node.checked,
            });
        }
        return obj;
    }

    function addAttendance() {
        let token = document.querySelector("meta[name='csrf-token']").getAttribute('content');

        let attendances = document.querySelectorAll("input[type='checkbox']");
        attendances = convertToJson(attendances);

        fetch('/api/addAttendance', {
            method: 'POST',
            headers: {'X-CSRF-TOKEN': token,},
            body: JSON.stringify({attendances})
        }).then(data => {
            console.log(data);
        })
    };
</script>
</html>
