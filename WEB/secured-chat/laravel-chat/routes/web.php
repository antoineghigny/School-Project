<?php

use Illuminate\Support\Facades\Route;
use App\Http\Middleware\privateConversations;

/*
|--------------------------------------------------------------------------
| Web Routes
|--------------------------------------------------------------------------
|
| Here is where you can register web routes for your application. These
| routes are loaded by the RouteServiceProvider within a group which
| contains the "web" middleware group. Now create something great!
|
*/


Auth::routes();
    Route::group(['middleware' => ['XSS']], function () {
        Route::group(array('before' => 'csrf'), function () {
            Route::middleware("auth")->group(function () {

                Route::redirect('/', '/login');
                Route::get('/home', [App\Http\Controllers\HomeController::class, 'index'])->name('private');

                Route::get('/private', [App\Http\Controllers\ConversationsController::class, 'index'])->name('private');
                Route::get('/private/{user}', [App\Http\Controllers\ConversationsController::class, 'show'])
                    ->middleware('can:talkTo,user')
                    ->name('conversations.show');

                Route::get('/users', [App\Http\Controllers\HomeController::class, 'friends'])->name('users');

                Route::get('/friendsRequest', [App\Http\Controllers\HomeController::class, 'requestFriends'])->name('friendsRequest');

                Route::get('/removeFriends', [App\Http\Controllers\HomeController::class, 'listUserToRemove'])->name('removeFriends');

                Route::get('/listUsers', [App\Http\Controllers\HomeController::class, 'displayUsers'])->name('displayUsers');
            });
        });
    });
