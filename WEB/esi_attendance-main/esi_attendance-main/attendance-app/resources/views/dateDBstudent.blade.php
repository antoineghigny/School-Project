<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="csrf-token" content="{{ csrf_token() }}">
    <title>Database</title>

</head>
<body>
    <h1>Check the attendances</h1>
    <label for="start">Choose a date:</label>
    <input type="date" id="start" name="trip-start"
           value="2022-09-01"
           min="2022-04-01" max="2023-09-01">
    <button type="submit" onclick="myFunction()">Check</button>
    <table id="attTable">
        <thead>
            <tr>
                <th>Date</th>
                <th>Student id</th>
                <th>Attendance</th>
            </tr>
        </thead>


    </table>
        <script>

            function myFunction() {
                let token = document.querySelector("meta[name='csrf-token']").getAttribute('content');
                let dateChoosen = document.getElementById("start").value;

                fetch('/api/dateDBstudent/'+dateChoosen,{
                    method: 'GET',
                    headers: {'X-CSRF-TOKEN': token},
                }).then(res=>
                    res.json().then(data=> ({
                        data: data,
                        status: res.status
                    })
                    ).then(res => {
                        console.log(res.data);

                        for(att of res.data.attendance){
                            let tr = document.createElement('tr');
                            let tdDate = document.createElement('td');
                            let tdStudentId = document.createElement('td');
                            let tdAttendance = document.createElement('td');
                            tdDate.innerHTML = att.date;
                            tdStudentId.innerHTML = att.student_id;
                            tdAttendance.innerHTML;
                            if(att.present === 1){
                                tdAttendance.innerHTML = "Present";
                            }
                            else{
                                tdAttendance.innerHTML = "Absent";
                            }
                            tr.appendChild(tdDate);
                            tr.appendChild(tdStudentId);
                            tr.appendChild(tdAttendance);
                            document.getElementById('attTable').appendChild(tr);
                        }

                })
                )
            }
        </script>
</body>
</html>
