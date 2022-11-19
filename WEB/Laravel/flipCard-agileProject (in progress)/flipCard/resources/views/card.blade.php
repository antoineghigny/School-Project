@extends('canevas')
@section('title', 'Carte')
@section('content')

    <div id="questionCard"><p id="question">{{$card[0]}}</p></div>
    <button id="btnAnswer" onclick="showAnswer()">Réponse</button>
    <script>
        function showAnswer() {
            $("#question").text("{{$card[1]}}")
            $("#btnAnswer").hide();
        }
    </script>
@endsection
