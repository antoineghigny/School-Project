<?php

namespace Database\Seeders;

use Illuminate\Database\Seeder;
use Illuminate\Support\Facades\DB;

class StudentsTableSeeder extends Seeder
{
    /**
     * Run the database seeds.
     *
     * @return void
     */
    public function run()
    {
        DB::table('students')->insert([[
            'id_student' => 11111,
            'firstname' => 'John',
            'lastname' => 'Doe',
            'group' => 'E11'
        ],[
            'id_student' => 22222,
            'firstname' => 'Jane',
            'lastname' => 'Ane',
            'group' => 'E13'
            ],
            [
                'id_student' => 33333,
                'firstname' => 'Joy',
                'lastname' => 'Jill',
                'group' => 'E12'
            ]]
        );
    }
}
