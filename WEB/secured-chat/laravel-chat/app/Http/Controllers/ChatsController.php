<?php

namespace App\Http\Controllers;

use App\Events\PrivateMessageSent;
use App\Http\Requests\CheckMessage;
use App\Models\discussion;
use App\Models\User;
use Illuminate\Auth\AuthManager;
use Illuminate\Contracts\Encryption\DecryptException;
use Illuminate\Contracts\Foundation\Application;
use Illuminate\Contracts\View\Factory;
use Illuminate\Contracts\View\View;
use Illuminate\Database\Eloquent\Builder;
use Illuminate\Database\Eloquent\Collection;
use Illuminate\Http\Request;
use Illuminate\Support\Facades\Auth;
use App\Models\Message;
use App\Events\MessageSent;
use App\Models\Friend;
use Illuminate\Support\Facades\Crypt;
use Illuminate\Support\Facades\Log;
use Illuminate\Support\Facades\Storage;
use Illuminate\Support\Facades\Validator;
use PhpParser\Node\Scalar\MagicConst\File;

class ChatsController extends Controller
{

    public function __construct()
    {
        $this->middleware('auth');
    }

    /**
     * It returns the view called chat
     *
     * @return Application|Factory|View
     */
    public function index()
    {
        return view('chat');
    }

    /**
     * It's getting the id of the discussion between the two users, then it's getting all the messages between the two
     * users and decrypting them
     *
     * @param User $user user The user you want to send a message to.
     * @return Builder[]|Collection It's returning all the messages between the two users.
     */
    public function privateMessages(User $user)
    {
        $allMessagesBetweenUsers = Message::with('user')
            ->where(['user_id' => auth()->id(), 'receiver_id' => $user->id])
            ->orWhere(function ($query) use ($user) {
                $query->where(['user_id' => $user->id, 'receiver_id' => auth()->id()]);
            })->get();

        foreach ($allMessagesBetweenUsers as $messagesBetweenUser) {
            try {
                $messagesBetweenUser['message'] = Crypt::decryptString($messagesBetweenUser['message']);
            } catch (DecryptException $e) {
            }
        }
        return $allMessagesBetweenUsers;
    }

    /**
     * It creates a new message and broadcasts it to all users except the sender
     *
     * @param Request $request
     * @param int friend The id of the user you want to send the message to.
     *
     * @return string[] status of the message sent.
     */
    public function sendPrivateMessage(CheckMessage $request, int $friend)
    {
        $user = Auth::user();
        $message = $user->messages()->create([
            'receiver_id' => $friend,
            'message' => Crypt::encryptString($request->input('message'))
        ]);

        $lastMessage = Message::where(['user_id' => auth()->id(), 'receiver_id' => $friend])
            ->orWhere(function ($query) use ($user) {
                $query->where(['user_id' => $user->id, 'receiver_id' => auth()->id()]);
            })
            ->latest()->first();

        try {
            $lastMessage['message'] = Crypt::decryptString($lastMessage['message']);
        } catch (DecryptException $e) {
        }

        broadcast(new PrivateMessageSent($friend, $user, json_encode($lastMessage)))->toOthers();
        return ['message' => $lastMessage];
    }


    /**
     * > It checks if the user and the friend are already friends, if not, it creates a new friend request
     *
     * @param int friend The user id of the person you want to add as a friend.
     *
     * @return string[] array with a key of status and a value of the message.
     */
    public function addFriend(int $friend)
    {
        $user = auth()->id();
        $friendExist = Friend::where([
            ['user_id', '=', $user], // user = 4
            ['receiver_id', '=', $friend]]) // friend = 3
        ->orWhere([ // OU
            ['user_id', '=', $friend], // user = 3
            ['receiver_id', '=', $user] // friend = 4
        ])->exists();

        if (!$friendExist) {
            Friend::create([
                'user_id' => $user,
                'receiver_id' => $friend
            ]);
            return ['status' => 'Request sent successfully'];
        } else {
            return ['status' => 'You are already a friend, something must have happened'];
        }
    }

    public function acceptFriend(int $friend)
    {
        $user = auth()->id();
        Friend::where('receiver_id', $user)
            ->where('user_id', $friend)
            ->update(['status' => true]);

        return ['status' => "Demande d'ami acceptée"];
    }

    public function removeFriends(int $friend)
    {
        $authUser = auth()->id();
        Friend::where(['user_id' => $authUser, 'receiver_id' => $friend])
            ->orWhere(['user_id' => $friend, 'receiver_id' => $authUser])->delete();
    }
}
# data remanence attack = CSRF
# birthday attack = salt
# Est-ce que la personne à qui tu parles est bien sami ? CSRF
