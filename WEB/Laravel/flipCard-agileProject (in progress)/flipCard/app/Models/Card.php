<?php

namespace App\Models;

use Illuminate\Database\Eloquent\Factories\HasFactory;
use Illuminate\Database\Eloquent\Model;
use Carbon\Carbon;

/**
 * Class Card
 * This class represent a card in the database.
 * @package App\Models
 * @author g55019|g56359
 */
class Card extends Model
{
    use HasFactory;
    public $timestamps = false;
    protected $fillable = ['question', 'answer'];

    /**
     * Create a new card in the database
     * @param array $data
     * @return void
     */
    public static function createCard($data)
    {
        Card::create([
            'question' => $data['question'],
            'answer' => $data['answer']
        ]);
    }

    /**
     * Update a card in the database
     * @param int $id
     * @param string $question
     * @param string $answer
     * @return void
     */
    public static function updateCard($id, $question, $answer)
    {
        $card = Card::find($id);
        $card->question = $question;
        $card->answer = $answer;
        $card->save();
    }

    /**
     * Update a card in the datebase, it updates its factorE
     */
    private static function updateFactorE($id, $factorE){
        $card = Card::find($id);
        $card->factorE = $factorE;
        $card->save();
    }

    /**
     * Update a card in the datebase, it updates its factorE
     * it finds the card by his question
     */
    public static function updateFactorEByQuestion($question, $factorE)
    {
        $card = Card::where('question', $question)->first();
        $card->factorE = $factorE;
        $card->save();
    }


    /**
     * Update a card in the datebase, it updates its intervalN
     */
    public static function resetIntervalN($id){
        $card = Card::find($id);
        $card->intervalN = 0;
        $card->save();
    }

    /**
     * Update a card in the datebase, it updates its intervalN
     * find the card by it's question
     */
    public static function resetIntervalNByQuestion($question){
        $card = Card::where('question', $question)->first();
        $card->intervalN = 0;
        $card->save();
    }

    /**
     * Update a card in the datebase, it increments its internvalN
     */
    public static function incrementIntervalN($id)
    {
        $card = Card::find($id);
        $card->intervalN = $card->intervalN + 1;
        $card->save();
    }

    /**
     * Update a card in the datebase, it increments its internvalN.
     * It use the question to find the card in the database
     * ONLY FOR TEST
     */
    public static function incrementIntervalNByQuestion($question){
        $card = Card::where('question', $question)->first();
        $card->intervalN = $card->intervalN + 1;
        $card->save();
    }


    /**
     * Update a card in the database, it updates its predictedDate
     */
    public static function updatePredictedDate($id, $ndDaysToAdd){
        $card = Card::find($id);
        $dateTmp = new Carbon($card->predictedDate);
        $card->predictedDate = $dateTmp->addDays($ndDaysToAdd);
        $card->save();
    }

    /**
     * Update a card in the database, it updates its predictedDate
     * it use the question to find the card in the database
     */
    public static function updatePredictedDateByQuestion($question, $ndDaysToAdd)
    {
        $card = Card::where('question', $question)->first();
        $dateTmp = new Carbon($card->predictedDate);
        $card->predictedDate = $dateTmp->addDays($ndDaysToAdd);
        $card->save();
    }

    public static function getLastCard(){
        //Get the card with the most recent predicteddate
        $card = Card::orderBy('predictedDate', 'asc')->first();
        return $card;
    }


    /**
     * Calculer la nouvelle valeur du facteur E
     * EF':=EF+(0.1-(5-q)*(0.08+(5-q)*0.02))
     * Notez que pour q=4, le facteur E ne change pas.
     * EF' - nouvelle valeur du facteur E
     * EF - ancienne valeur du facteur E
     * q - qualité de la réponse
     * f - fonction utilisée pour calculer EF'.
     */
    public static function calculateEF($id, $EF, $q)
    {
        $newEF = $EF + (0.1 - (5 - $q) * (0.08 + (5 - $q) * 0.02));
        if ($newEF < 1.3) {
            $newEF = 1.3;
        }
        else if($newEF > 2.5){
            $newEF = 2.5;
        }
        self::updateFactorE($id, $newEF);
        return $newEF;
    }

    /**
     * Calculer les intervalles entre répétitions :
     *  I(1):=1
     *  I(2):=6
     *  pour n>2 I(n):=I(n-1)*EF
     *
     *  où :
     *  I(n) - intervalle entre les répétitions après la nième répétition (en jours)
     *  EF - facteur de facilité reflétant la facilité de mémorisation et
     *  de maintien en mémoire d'un élément donné (appelé plus tard le facteur E)
     */

    public static function calculateInterval($id, $qualityAnswer)
    {

        $card = Card::find($id);
        $n = $card->intervalN;
        $EF = $card->factorE;
        $I = $card->predictedDate;

        $EF = self::calculateEF($id, $EF, $qualityAnswer);

        if($qualityAnswer == 0){
            self::resetIntervalN($id);
        }
        else{
            self::incrementIntervalN($id);
        }

        switch($n) {
            case 0:
                self::updatePredictedDate($id, 1);
                break;

            case 1:
                self::updatePredictedDate($id, 6);
                break;

            default:
                $I = round(($n -1) * $EF);
                self::updatePredictedDate($id, $I);
        }
        //Si n = 0, I = 1
        //Si n = 1, I = 6
        //Sinon I = (I * EF) à arrondir
        // N++ à chaque fois
        //Si répond c'est oublié -> n = 0
    }

}
