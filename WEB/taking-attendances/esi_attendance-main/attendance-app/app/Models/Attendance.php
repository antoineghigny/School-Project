<?php

namespace App\Models;


use Illuminate\Database\Eloquent\Model;
use Illuminate\Support\Facades\Date;

class Attendance extends Model
{
    protected $table = 'attendance';
    protected $fillable = ['date', 'student_id', 'present'];
    protected $connection = 'sqlite';
    public $timestamps = false;

    public static function getAll()
    {
        return Attendance::all();
    }

    public static function getAttendance($date)
    {
        return Attendance::where('date', $date)->get();
    }

    public static function addAttendance($attendances)
    {
        foreach ($attendances['attendances'] as $attendance) {
            var_dump($attendance);
            Attendance::create([
                    'date' => Date::now(),
                    'student_id' => $attendance['id'],
                    'present' => $attendance['present']
                ]
            );
        }
    }

    public static function inAttendance(mixed $date)
    {
        return Attendance::where('date', $date)->exists();
    }


}
