<?php

namespace App\Models;

use Illuminate\Database\Eloquent\Model;

class Student extends Model
{
    protected $table = 'students';
    protected $primaryKey = 'id';
    protected $fillable = ['id_student','firstname', 'lastname', 'group'];
    protected $connection = 'sqlite';
    public $timestamps = false;

    public static function getStudents()
    {
        return Student::all();
    }

    public static function addStudent($data)
    {

        if (Student::where('id_student', $data['id_student'])->exists()) {
            return false;
        } else {
            if($data['firstname'] == null || $data['lastname'] == null){
                return false;
            }
        }

        if ($data['id_student'] == "" && $data['id_student'] == null) {
            $data['id_student'] = null;
        }

        Student::create([
            'id_student' => $data['id_student'],
            'firstname' => $data['firstname'],
            'lastname' => $data['lastname'],
            'group' => $data['group'],
        ]);
    }

    public static function deleteStudent($id)
    {
        Student::where('id_student', $id)->delete();
    }

    public static function editStudent($data)
    {
        Student::where('id_student', $data['id_student'])->update([
            'firstname' => $data['firstname'],
            'lastname' => $data['lastname'],
            'group' => $data['group'],
        ]);
    }

}
