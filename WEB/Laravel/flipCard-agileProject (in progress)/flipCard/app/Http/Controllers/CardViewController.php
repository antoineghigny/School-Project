<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;

class CardViewController extends Controller
{
    public function cardsView(){
        $cardController = new CardController();
        return view('cardlist', ['cards' => $cardController->getAllCards()]);
    }

    public function testQuestion() {
        $card = ["Quel âge avez-vous ?", "30 ans"];
        return view("card", ['card' => $card]);
    }
}
