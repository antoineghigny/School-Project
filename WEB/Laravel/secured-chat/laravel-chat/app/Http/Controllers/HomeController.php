<?php

namespace App\Http\Controllers;

use App\Models\Friend;
use App\Models\User;

use Illuminate\Contracts\Foundation\Application;
use Illuminate\Contracts\View\Factory;
use Illuminate\Contracts\View\View;
use Illuminate\Http\Request;
use Illuminate\Validation\Rules\NotIn;

class HomeController extends Controller
{
    /**
     * Create a new controller instance.
     *
     * @return void
     */
    public function __construct()
    {
        $this->middleware('auth');
    }

    /**
     * Show the application dashboard.
     *
     * @return \Illuminate\Contracts\Support\Renderable
     */
    /**
     * The function index() returns the view home
     *
     * @return Application|Factory|View
     */
    public function index()
    {
        return view('home');
    }

    /**
     * It returns all the users in the database
     *
     * @return All the users in the database.
     */
    public function user()
    {
        return User::all();
    }

    /**
     * It returns a view of all users who are not friends with the authenticated user
     *
     * @return Application|Factory|View
     */
    public function friends()
    {
        $items = array();

        $authUser = auth()->id();
        $select1 = Friend::select('*')
            ->where('user_id', $authUser)
            ->join('users', 'users.id', '=', 'friends.user_id')->get();

        $select2 = Friend::select('*')
            ->where('receiver_id', $authUser)
            ->join('users', 'users.id', '=', 'friends.receiver_id')->get();

        foreach ($select1 as $username) {
            $items[] = $username->receiver_id;
        }
        foreach ($select2 as $username) {
            $items[] = $username->user_id;
        }
        $items[] = auth()->id();

        return view('friends', ['friends' => User::all()->whereNotIn('id', $items)]);
    }

    /**
     * It returns a view with a list of users who have sent a friend request to the logged in user
     *
     * @return Application|Factory|View
     */
    public function requestFriends()
    {
        $user = auth()->id();
        $items = array();

        $select1 = Friend::select('user_id')
            ->where('receiver_id', $user)
            ->where('status', false)
            ->get();

        foreach ($select1 as $friendsUser) {
            $items[] = $friendsUser->user_id;
        }

        return view('friendsRequest', ['friends' => User::all()->whereIn('id', $items)]);
    }

    /**
     * It returns a list of all users that are friends with the authenticated user
     *
     * @return Application|Factory|View
     */
    public function listUserToRemove()
    {
        $authUser = auth()->id();
        $items = array();

        $select1 = Friend::select('receiver_id')
            ->where([
                ['user_id', '=', $authUser], // user = 4
                ['status', '=', true]])->get();

        $select2 = Friend::select('user_id')
            ->where([
                ['status', '=', true], // user = 3
                ['receiver_id', '=', $authUser] // friend = 4
            ])->get();

        foreach ($select1 as $username) {
            $items[] = $username->receiver_id;
        }
        foreach ($select2 as $username) {
            $items[] = $username->receiver_id;
        }

        return view('removeFriends', ['friends' => User::all()->whereIn('id', $items)]);
    }

    /**
     * Display a listing of the resource.
     *
     * @return Application|Factory|View
     */
    public function displayUsers()
    {
        $users = User::select("*")
            ->whereNotNull('last_seen')
            ->orderBy('last_seen', 'DESC')
            ->paginate(10);

        return view('users', compact('users'));
    }
}
