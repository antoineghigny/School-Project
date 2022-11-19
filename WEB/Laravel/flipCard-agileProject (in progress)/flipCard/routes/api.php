<?php

use Illuminate\Http\Request;
use Illuminate\Support\Facades\Route;
use App\Http\Controllers\CardController;


Route::middleware('auth:sanctum')->get('/user', function (Request $request) {
    return $request->user();
});

Route::get('/cards', [CardController::class, 'getAllCards']);
Route::post('/card', [CardController::class, 'getOneCard']);
Route::get('/card/{id}', [CardController::class, 'getOneCard']);
Route::patch('/card/{id}', [CardController::class, 'updateOneCard']);
Route::post('/card/create', [CardController::class, 'addNewCard']);
Route::delete('/card/{id}', [CardController::class, 'deleteOneCard']);
Route::post('/learning', [CardController::class, 'responseCard']);

