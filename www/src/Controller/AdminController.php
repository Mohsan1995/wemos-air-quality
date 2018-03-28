<?php
// src/Controller/ApiController.php
namespace App\Controller;


use FOS\RestBundle\Controller\Annotations as Rest;
use FOS\RestBundle\View\View;
use Psr\Container\ContainerInterface;
use Symfony\Bundle\FrameworkBundle\Controller\Controller;
use Symfony\Component\HttpFoundation\JsonResponse;
use Symfony\Component\HttpFoundation\Response;
use Symfony\Component\Routing\Annotation\Route;
use Twig\Environment;

/**
 *
 * @Route("/admin")
 */

class AdminController extends Controller
{

    /**
     * @Route(name="admin_index", path="/")
     *
     */
    public function index(){
        return new Response("CONNECTED");
    }
}