@extends ('layouts.app')
@section ('content')
    <div class="container">
        <div class="row">
            @include ('conversations.users', ['users' => $users])
            <div class="col-md-9">
                <div class="card-header">{{ $user->name }}</div>
                <div class="card-body conversations">
                    @include ('./chat', ['users' => $users], ['user' => $user])
                </div>
            </div>
        </div>
    </div>
@endsection
