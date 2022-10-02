<?php

namespace App\Http\Controllers;

use App\Models\Message;

use App\Models\User;
use Illuminate\Auth\AuthManager;
use Illuminate\Contracts\Foundation\Application;
use Illuminate\Contracts\View\Factory;
use Illuminate\Contracts\View\View;
use Illuminate\Support\Facades\Cache;
use Illuminate\Support\Request;
use Illuminate\Support\Facades\Auth;

class ConversationsController extends Controller
{

    private $conversationRepository;

    private $auth;

    public function __construct(ConversationRepository $conversationRepository, AuthManager $auth)
    {
        $this->conversationRepository = $conversationRepository;
        $this->auth = $auth;
    }

    /**
     * It returns a view of the conversations/index page, which is populated with the conversations of the currently logged
     * in user
     *
     * @return Application|Factory|View
     */
    public function index()
        /**
         * It returns a view with a list of conversations and a user
         *
         * @param User user The user we're viewing the conversation with
         *
         * @return a view 'conversations/show' is being returned.
         */
    {
        return view('conversations/index', [
            'users' => $this->conversationRepository->getConversations($this->auth->user()->id),
        ]);
    }

    public function show(User $user)
    {
        return view('conversations/show', [
            'users' => $this->conversationRepository->getConversations($this->auth->user()->id),
            'user' => $user
        ]);
    }
}
