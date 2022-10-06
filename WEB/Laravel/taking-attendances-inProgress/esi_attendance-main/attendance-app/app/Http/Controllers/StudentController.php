<?php

namespace App\Http\Controllers;

use App\Models\Student;
use Illuminate\Http\Request;

class StudentController extends Controller
{

    public function index()
    {
        $students = Student::getStudents();
        return view('home', ['students' => $students]);
    }

    public function crud(){
        $students = Student::getStudents();
        return view('crudstudent', ['students' => $students] );
    }

    public function deleteStudent(Request $request){
        Student::deleteStudent($request->id);
        return $this->crud();

    }

    public function addStudent(Request $request){
        Student::addStudent($request->all());
        return $this->crud();
    }

    public function editStudent(Request $request){
        Student::editStudent($request->all());
        return $this->crud();
    }
}

