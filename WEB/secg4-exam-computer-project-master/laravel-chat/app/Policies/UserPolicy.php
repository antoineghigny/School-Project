<?php

namespace App\Policies;

use App\Models\Friend;
use App\Models\User;
use Illuminate\Auth\Access\HandlesAuthorization;

class UserPolicy
{
    use HandlesAuthorization;

    /**
     * > If the user is not the same as the receiver and the user is either the sender or the receiver, then return true
     *
     * @param User user The user who is trying to talk to another user.
     * @param User to The user you want to talk to
     */
    public function talkTo(User $user, User $to)
    {
        $select1 = Friend::select('receiver_id')
            ->where('user_id', $user->id)
            ->where('receiver_id', $to->id)->exists();

        $select12 = Friend::select('user_id')
            ->where('receiver_id', $user->id)
            ->where('user_id', $to->id)->exists();
        return $user->id != $to->id && ($select1 || $select12);
    }
}
