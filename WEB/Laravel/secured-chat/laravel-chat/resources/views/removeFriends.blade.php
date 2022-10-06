@extends('layouts.app')
@section('content')
    <remove-friends v-on:removefriend="removeFriend" :friends="{{$friends}}"></remove-friends>
@endsection
