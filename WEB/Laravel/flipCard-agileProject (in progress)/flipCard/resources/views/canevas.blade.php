<!DOCTYPE html>
<html lang="fr">

<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.5.1/jquery.min.js"></script>
    <link rel="stylesheet" href="https://www.w3schools.com/w3css/4/w3.css">
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.7.0/css/font-awesome.min.css">
    <link rel="stylesheet" href="{{ asset('./css/style.css') }}">
    <link href="https://fonts.googleapis.com/css2?family=Aclonica&display=swap" rel="stylesheet">
    <title>@yield('title')</title>
    @yield('style')
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
</head>

<body>
    <header>
    </header>
    <menu>
        <h1 id="title">Flip Card</h1>
        <p><a href={{route("testQuestion")}}>Cartes</a></p>
        <p><a href={{route("cardsView")}}>Liste des cartes</a></p>
        <p><a href={{route("learning")}}>Mode apprentissage</a></p>
    </menu>
    <main>
        @yield('content')
    </main>
    <footer>@yield('footer')</footer>
</body>

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

</html>
