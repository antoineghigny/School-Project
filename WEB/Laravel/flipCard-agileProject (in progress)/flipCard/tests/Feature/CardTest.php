<?php

namespace Tests\Feature;

use App\Models\Card;

use Carbon\Carbon;
use Illuminate\Foundation\Testing\RefreshDatabase;
use Tests\TestCase;

class CardTest extends TestCase
{

    use RefreshDatabase;

    /**
     * Test the creation of a card
     * @return void
     */
    public function testCreateCardModel()
    {
        $data = [
            'question' => 'What is the capital of France?',
            'answer' => 'Paris'
        ];
        Card::createCard($data);
        $this->assertDatabaseHas('cards', [
            'question' => 'What is the capital of France?',
            'answer' => 'Paris',
        ]);
    }

    /**
     * Test the creation of a card with the API
     * @return void
     */
    public function testCreateCardApi()
    {
        $data = [
            'question' => 'What is the capital of France?',
            'answer' => 'Paris'
        ];

        $response = $this->postJson('api/card/create', $data);
        $response->assertStatus(302);

        $this->assertDatabaseHas('cards', [
            'question' => 'What is the capital of France?',
            'answer' => 'Paris',
        ]);
    }

    /**
     * test the suppresion of a card with the model
     * @return void
     */

    public function testDeleteCardModel(){
        $data = [
            'question' => 'What is the capital of France?',
            'answer' => 'Paris'
        ];

        Card::createCard($data);
        $card = Card::where('question', 'What is the capital of France?')->first();
        $card->delete();
        $this->assertDatabaseMissing('cards', [
            'question' => 'What is the capital of France?',
            'answer' => 'Paris',
        ]);
    }

    /**
     * test the suppresion of a card with the API
     * @return void
     */
    public function testDeleteCardApi(){
        $data = [
            'question' => 'What is the capital of France?',
            'answer' => 'Paris'
        ];

        Card::createCard($data);

        $response = $this->deleteJson('api/card/1');
        $response->assertStatus(302);
    }

    /**
     * test the update of a card with the model
     * @return void
     */
    public function testUpdateCardModel()
    {
        $data = [
            'question' => 'What is the capital of France?',
            'answer' => 'Paris'
        ];

        Card::createCard($data);

        Card::updateCard(1, 'What is the capital of Germany?', 'Berlin');

        $this->assertDatabaseHas('cards', [
            'question' => 'What is the capital of Germany?',
            'answer' => 'Berlin',
        ]);
    }

    /**
     * test the update of a card with the API
     * @return void
     */
    public function testUpdateCardApi(){
        $data = [
            'question' => 'What is the capital of France?',
            'answer' => 'Paris'
        ];
        Card::createCard($data);

        $data = [
            'id' => 1,
            'question' => 'What is the capital of BE?',
            'answer' => 'Bxl'
        ];

        $response = $this->patchJson('api/card/1', $data);
        $response->assertStatus(302);
    }

    /**
     * test default value factorE of a card with the model
     * @return void
     */
    public function testUpdateFactorECardModel(){
        $data = [
            'question' => 'What is the capital of France?',
            'answer' => 'Paris'
        ];
        Card::createCard($data);

        $this->assertDatabaseHas('cards', [
            'question' => 'What is the capital of France?',
            'answer' => 'Paris',
            'factorE' => 2.5,
        ]);
    }

    /**
     * test default update factorE of a card with the model
     * @return void
     */

    public function testUpdateFactorECardModel2()
    {
        $data = [
            'question' => 'What is the capital of France?',
            'answer' => 'Paris'
        ];
        Card::createCard($data);

        Card::updateFactorEByQuestion('What is the capital of France?', 1.5);

        $this->assertDatabaseHas('cards', [
            'question' => 'What is the capital of France?',
            'answer' => 'Paris',
            'factorE' => 1.5,
        ]);
    }

    /**
     * Test default value of IntervalN
     */
    public function testDefaultIntervalNCardModel()
    {
        $data = [
            'question' => 'What is the capital of France?',
            'answer' => 'Paris'
        ];
        Card::createCard($data);

        $this->assertDatabaseHas('cards', [
            'question' => 'What is the capital of France?',
            'answer' => 'Paris',
            'intervalN' => 0,
        ]);
    }

    /**
     * Test increment  of IntervalN
     */
    public function testIncrementIntervalNCardModel(){
        $data = [
            'question' => 'What is the capital of France?',
            'answer' => 'Paris'
        ];
        Card::createCard($data);

        Card::incrementIntervalNByQuestion('What is the capital of France?');

        $this->assertDatabaseHas('cards', [
            'question' => 'What is the capital of France?',
            'answer' => 'Paris',
            'intervalN' => 1,
        ]);
    }

    /**
     * Test reset of IntervalN
     */
    public function testResetIntervalNCardModel()
    {
        $data = [
            'question' => 'What is the capital of France?',
            'answer' => 'Paris'
        ];
        Card::createCard($data);
        Card::incrementIntervalNByQuestion('What is the capital of France?');
        Card::resetIntervalNByQuestion('What is the capital of France?');
        $this->assertDatabaseHas('cards', [
            'question' => 'What is the capital of France?',
            'answer' => 'Paris',
            'intervalN' => 0,
        ]);
    }

    /**
     * Test of default predictedDate
     */
    public function testDefaultPredictedDateCardModel(){
        $data = [
            'question' => 'What is the capital of France?',
            'answer' => 'Paris'
        ];
        Card::createCard($data);

        $this->assertDatabaseHas('cards', [
            'question' => 'What is the capital of France?',
            'answer' => 'Paris',
            'predictedDate' => Carbon::now(),
        ]);
    }

    /**
     * Test of increment predictedDate
     */
    public function testIncrementPredictedDateCardModel()
    {
        $data = [
            'question' => 'What is the capital of France?',
            'answer' => 'Paris'
        ];
        Card::createCard($data);

        Card::updatePredictedDateByQuestion('What is the capital of France?', 2);

        $this->assertDatabaseHas('cards', [
            'question' => 'What is the capital of France?',
            'answer' => 'Paris',
            'predictedDate' => Carbon::now()->addDays(2),
        ]);
    }


}
