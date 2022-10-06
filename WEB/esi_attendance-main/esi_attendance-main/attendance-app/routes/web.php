<?php

use App\Http\Controllers\AttendanceCheckController;
use Illuminate\Support\Facades\Route;
use App\Http\Controllers\StudentController;



Route::get('/', [StudentController::class, 'index']);

Route::get('/dateDBstudent', [AttendanceCheckController::class, 'index']);

Route::get('/crudstudent', [StudentController::class, 'crud']);

Route::post('add', [AttendanceCheckController::class, 'addAttendance']);

Route::post('/crudstudent', [StudentController::class, 'addStudent'])->name('student.store');

Route::post('/deletestudent', [StudentController::class, 'deleteStudent'])->name('student.delete');

Route::post('/editstudent', [StudentController::class, 'editStudent'])->name('student.edit');
