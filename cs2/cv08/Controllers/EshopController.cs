using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.Filters;

namespace cv08;

public class EshopController : Controller
{
    private readonly ProductService _productService;
    private readonly CartServices _cartServices;

    public EshopController(ProductService productService, CartServices cartServices)
    {
        this._productService = productService;
        this._cartServices = cartServices;
    }

    public override void OnActionExecuting(ActionExecutingContext ctx)
    {
        ViewBag.ProductCount = _cartServices.count;
        base.OnActionExecuting(ctx);
    }

    public IActionResult Index()
    {
        this.ViewBag.Products = _productService.List(); 
        
        return View();
    }
    
    public IActionResult Details(int id)
    {
        Product? p = this._productService.Find(id);
        if (p is null)
        {
            return NotFound();
        }
        
        ViewBag.Product = p;
        return View();
    }

    public IActionResult AddToCart(int id)
    {
        this._cartServices.count++;
        return RedirectToAction("Details", new { id = id });
    }
}