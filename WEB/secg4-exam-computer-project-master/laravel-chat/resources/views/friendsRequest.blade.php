@extends('layouts.app')
@section('content')
    <friend-request v-on:friendaccept="acceptFriend" v-on:refuserequest="removeFriend" :friends="{{$friends}}"></friend-request>
@endsection
