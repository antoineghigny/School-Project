@extends('canevas')
@section('title', 'Apprentissage')
@section('content')

@section('style')
    <link rel="stylesheet" href="{{ asset('./css/cardlist.css') }}">
@endsection

<div class="center-items">
    @if($cards == null)
        Pas de carte
    @else
            <div class="card-container card-container-learning">
                <div class="card">
                    <div class="card__face card__face--front">
                        <p class="question-title">{{ $cards->question }}</p>
                    </div>
                    <div class="card__face card__face--back">
                        <i class="cancel-icon fa fa-2x fa-times" aria-hidden="true"></i>
                        <p class="answer-title" name="answer" required>{{ $cards->answer }}</p>
                    </div>
                </div>
        </div>
    @endif
    <form action="api/learning" method="post">
        <input type="hidden" name="id" value="{{$cards->id}}">
        <button name="answerValue" value=5 type="submit">Facile</button>
        <button name="answerValue" value="4" type="submit">Correct</button>
        <button name="answerValue" value="1" type="submit">A revoir</button>
        <button name="answerValue" value=0 type="submit">Je ne sais pas</button>
    </form>
</div>
@endsection
