<div class="col-md-3">
    <div class="list-group">
        @foreach($users as $user)
            @if(Cache::has('user-is-online-' . $user->id))
                <a class="list-group-item text-success" href="{{route ('conversations.show', $user->id) }}">
                    {{$user->name}} - Online
                </a>
            @else
                <a class="list-group-item text-danger" href="{{route ('conversations.show', $user->id) }}">
                    {{$user->name}} - Offline
                </a>
            @endif
        @endforeach
    </div>
</div>

