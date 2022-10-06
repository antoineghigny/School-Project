<?php

namespace App\Http\Controllers;

use App\Models\Friend;
use App\Models\User;

class ConversationRepository
{
    public function getConversations(int $userId)
    {
        /* Getting all the users from the database. */
        $users = User::all();
        $items = array();

        $authUser = auth()->id();

        $select1 = Friend::select('receiver_id')
            ->where('user_id', $authUser)
            ->where('status', true)
            ->get();

        $select2 = Friend::select('user_id')
            ->where('receiver_id', $authUser)
            ->where('status', true)
            ->get();

        foreach ($select1 as $username) {
            $items[] = $username->receiver_id;
        }
        foreach ($select2 as $username) {
            $items[] = $username->user_id;
        }
        return User::all()->whereIn('id', $items);
    }
}
