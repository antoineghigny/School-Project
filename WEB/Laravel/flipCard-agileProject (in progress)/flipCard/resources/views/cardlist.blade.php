@extends('canevas')
@section('title', 'Carte')
@section('content')

@section('style')
    <link rel="stylesheet" href="{{ asset('./css/cardlist.css') }}">
@endsection

<div class="card-list">
    <div class="card-container">
        <div class="card">
            <div class="card__face card__face--front">
                <div class="plus-icon">
                    <i class="fa fa-5x fa-plus"></i>
                </div>
            </div>
            <div class="card__face card__face--back">
                <i class="cancel-icon fa fa-2x fa-times" aria-hidden="true"></i>
                <form action="{{ url('/api/card/create') }}" method="POST" class="card-form">
                    @csrf
                    <div class="form-input">
                        <label for="question">question</label>
                        <textarea name="question" required></textarea>
                    </div>
                    <div class="form-input">
                        <label for="answer">answer</label>
                        <textarea name="answer" required></textarea>
                    </div>
                    <button class="submit-button" type="submit">Add</button>
                </form>
            </div>
        </div>
    </div>

    @foreach ($cards as $card)
        <div class="card-container">
            <div class="card">
                <div class="card__face card__face--front">
                    <p class="question-title">{{ $card->question }}</p>
                </div>
                <div class="card__face card__face--back">
                    <i class="cancel-icon fa fa-2x fa-times" aria-hidden="true"></i>
                    <form action="api/card/{{$card->id}}" method="POST">
                        @csrf
                        @method('delete')
                        <i class="delete-icon fa fa-2x fa-trash"></i>
                    </form>
                    <form action="/api/card/{{ $card->id }}" method="POST" class="card-form">
                        @csrf
                        @method('patch')
                        <div class="form-input" id="{{$card->id}}">
                            <label for="question">Question</label>
                            <textarea name="question" required>{{ $card->question }}</textarea>
                        </div>
                        <div class="form-input">
                            <label for="answer">Answer</label>
                            <textarea name="answer" required>{{ $card->answer }}</textarea>
                        </div>
                        <button class="submit-button" type="submit">Modify</button>
                    </form>
                </div>
            </div>
        </div>
    @endforeach
</div>

<script>
    $('.card .card__face--front').click(function () {
        $(this).parent().addClass('is-flipped')
    })
    $('.card .card__face--back .cancel-icon').click(function () {
        $(this).parent().parent().removeClass('is-flipped')
    })

    $('.card .card__face--back .delete-icon').click(function () {
        console.log("test")
            $("#modal-content, #modal-background").toggleClass("active");
    })
    $(".delete-icon").click(function () {
        $(this).parent().submit();
    });
</script>
@endsection
