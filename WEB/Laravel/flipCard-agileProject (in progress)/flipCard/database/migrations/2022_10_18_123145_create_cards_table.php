<?php

use Carbon\Carbon;
use Illuminate\Database\Migrations\Migration;
use Illuminate\Database\Schema\Blueprint;
use Illuminate\Support\Facades\DB;
use Illuminate\Support\Facades\Schema;

return new class extends Migration
{
    /**
     * Run the migrations.
     *
     * @return void
     */
    public function up()
    {
        Schema::create('cards', function (Blueprint $table) {
            $table->id();
            $table->string('question')->nullable(false)->unique();
            $table->string('answer')->nullable(false);
            $table->double('factorE')->default(2.5);
            $table->integer('intervalN')->default(0);
            $table->dateTime('predictedDate')->default(Carbon::now()->addDays(0))->nullable(false);
        });

        DB::table('cards')->insert([
            'question' => 'Quel âge avez-vous ?',
            'answer' => '30 ans',
        ]);

        DB::table('cards')->insert([
            'question' => 'Quel est votre nom ?',
            'answer' => 'Dupont',
        ]);
    }

    /**
     * Reverse the migrations.
     *
     * @return void
     */
    public function down()
    {
        Schema::dropIfExists('cards');
    }
};
