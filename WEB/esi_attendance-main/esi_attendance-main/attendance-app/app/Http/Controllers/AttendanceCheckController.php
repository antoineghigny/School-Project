<?php

namespace App\Http\Controllers;

use App\Models\Attendance;
use Illuminate\Http\Request;

class AttendanceCheckController extends Controller
{
    public function index()
    {
        return view('dateDBstudent');
    }

    public function getAttendance($date)
    {
        $attendances = Attendance::getAttendance($date);
        return response()->json(['attendance' => $attendances]);
    }

    public function addAttendance(Request $request)
    {
        $presences = $request->getContent();
        $presences = json_decode($presences, true);
        if(Attendance::inAttendance($presences)){ // not working because of the date format in the database
            return response()->json(['message' => 'Attendance already exists']);
        }else{
            Attendance::addAttendance();
            return response()->json(['message' => 'Attendance added']);
        }
    }
}
