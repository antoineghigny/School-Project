<?php

namespace App\Http\Controllers;

use App\Models\Card;
use Illuminate\Http\Request;

class CardController extends Controller
{
    public function getAllCards()
    {
        return Card::all();
    }

    /**
     * Find a card by its id
     * @param $id
     * @return mixed
     */
    public function getOneCard($id)
    {
        return Card::find($id);
    }

    /**
     * @param Request $request
     * @return \Illuminate\Http\RedirectResponse
     * Receive a Json with the question and the answer of the card. Use the method createCard from the model
     * to create the card in the database.
     */
    public function addNewCard(Request $request)
    {
        $question = $request->question;
        $answer = $request->answer;
        $data =
            [
                'question' => $question,
                'answer' => $answer
            ];
        Card::createCard($data);
        return redirect()->back();
    }

    /**
     * @param Request $request
     * @return \Illuminate\Http\RedirectResponse
     * Receive a Json with the id, the question and the answer of the card
     * it must get the value of the Json and use them to update a card
     */
    public function updateOneCard(Request $request)
    {
        $id = $request->id;
        $question = $request->question;
        $answer = $request->answer;

        Card::updateCard($id, $question, $answer);
        return redirect()->back();
    }

    /**
     * @param int $id
     * @return \Illuminate\Http\RedirectResponse
     * Receive the id of the card to delete
     * it must get the id and use it to delete a card
     */
    public function deleteOneCard($id)
    {
        Card::destroy($id);
        return redirect()->back();
    }

    public function learning(){
        $cards = Card::getLastCard();
        //dd($cards);
        return view("learning", ['cards' => $cards]);
    }

    /**
     * Function called by learning.blade.php by the fetch api with PATCH
     * this method receive a request that contains an id and a value
     * the id is the id of the card and the value is the value of the response
     * This id and the value are use with the function caclulateInterval and after that the page is refresh
     * @param Request $request
     * @return \Illuminate\Http\RedirectResponse
     */
    public function responseCard(Request $request){
        $id = $request->id;
        $value = $request->answerValue;
        Card::calculateInterval($id, $value);
        return redirect()->route('learning');
    }
    /**
     * $id = $request->id;
    $answerValue = $request->answerValue;
    Card::calculateInterval($id,$answerValue);
    $this->learning();
     */

}
