@extends('layouts.app')
@section('content')
    <friends v-on:friendsent="addFriend" :friends="{{$friends}}"></friends>
@endsection
