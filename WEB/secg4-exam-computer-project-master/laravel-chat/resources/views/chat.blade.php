@extends('layouts.app')
@section('content')
    <div class="container">
        <div class="row">
            @include ('conversations.users', ['users' => $users])
            <div class="col-md-9">
                <div class="card-header">{!! $user->name !!}</div>
                <div class="card-body conversations">
                    <div class="container">
                        <div class="card">
                            <div class="card-header">Chats</div>
                            <div class="card-body">
                                <chat-messages :messages="messages"></chat-messages>
                            </div>
                            <div class="card-footer">
                                <chat-form v-on:messagesent="addMessage" v-on:friendsent="fetchMessages" v-on:pushmessage="pushMessage"
                                           :user="{{ Auth::user() }}"
                                           :friend="{{$user}}"></chat-form>
                            </div>
                        </div>
                    </div>
                </div>
            </div>

        </div>
@endsection
