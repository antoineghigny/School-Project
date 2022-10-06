<?php

namespace App\Http\Middleware;

use Closure;
use Illuminate\Http\Request;
use App\Models\User;
use Illuminate\Support\Facades\Auth;
use Illuminate\Support\Facades\Cache;

class UserActivity
{

    /**
     * If the user is logged in, we'll set a cache key with the user's ID and a value of true. We'll also set an expiration
     * time of 2 minutes
     *
     * @param Request $request
     * @param Closure $next
     * @return value of the $next callback, or the first argument passed to the "after" method.
     */
    public function handle(Request $request, Closure $next)
    {
        if (Auth::check()) {
            $expiresAt = now()->addMinutes(2); /* already given time here we already set 2 min. */
            Cache::put('user-is-online-' . Auth::user()->id, true, $expiresAt);

            /* user last seen */
            User::where('id', Auth::user()->id)->update(['last_seen' => now()]);
        }

        return $next($request);
    }
}
