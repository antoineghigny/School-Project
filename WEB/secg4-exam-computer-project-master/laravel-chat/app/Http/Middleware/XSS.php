<?php

namespace App\Http\Middleware;

use Closure;
use Illuminate\Http\Request;

class XSS
{

    /**
     * It takes the user input, strips all HTML tags from it, and then merges it back into the request
     *
     * @param Request $request
     * @param Closure $next
     * @return request is being returned with the user input stripped of tags.
     */
    public function handle(Request $request, Closure $next)
    {
        $userInput = $request->all();
        array_walk_recursive($userInput, function (&$userInput) {
            $userInput = strip_tags($userInput);
        });
        $request->merge($userInput);
        return $next($request);
    }
}
