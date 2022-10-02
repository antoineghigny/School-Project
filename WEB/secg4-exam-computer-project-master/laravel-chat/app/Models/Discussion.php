<?php

namespace App\Models;

use Illuminate\Database\Eloquent\Factories\HasFactory;
use Illuminate\Database\Eloquent\Model;

class Discussion extends Model
{
    use HasFactory;
    protected $fillable = ['user_id', 'receiver_id'];
    protected $connection = 'sqlite';
    public $timestamps = false;
    public $table = 'discussions';
}
