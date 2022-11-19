<?php

use App\Http\Controllers\CardController;
use App\Http\Controllers\CardViewController;
use Illuminate\Support\Facades\Route;

/*
|--------------------------------------------------------------------------
| Web Routes
|--------------------------------------------------------------------------
|
| Here is where you can register web routes for your application. These
| routes are loaded by the RouteServiceProvider within a group which
| contains the "web" middleware group. Now create something great!
|upda
*/





Route::redirect('/', '/cards');
Route::get('/card', [CardViewController::class, "testQuestion"])->name("testQuestion");
Route::get('/cards', [CardViewController::class, 'cardsView'])->name("cardsView");
Route::get('/learning', [CardController::class, "learning"])->name("learning");
//Route::post('/learning', [CardController::class, "responseCard"]);
