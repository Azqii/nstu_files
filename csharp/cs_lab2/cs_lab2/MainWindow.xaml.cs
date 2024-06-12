using System.IO;
using System.Windows;

namespace cs_lab2;

using Core.Models;
using System.Collections.Generic;
using System.Threading;
using System.Windows.Controls;
using System.Windows.Media.Imaging;


/// <summary>
/// Interaction logic for MainWindow.xaml
/// </summary>
public partial class MainWindow : Window {
    private static readonly Random Rand = new Random();

    private List<Seller> SellersList { get; set; } = [];
    private List<Manager> ManagersList { get; set; } = [];

    private static readonly object Object = new();
    private bool _started;
    private Thread _firstThread;
    private Thread _secondThread;

    public MainWindow() {
        InitializeComponent();

        for (var i = 0; i < Rand.Next(5, 11); i++) {
            SellersList.Add(new Seller(
                null, null, null, null,
                Rand.Next(10, 350), Rand.Next(450)
            ));
        }

        for (var i = 0; i < Rand.Next(5, 11); i++) {
            ManagersList.Add(new Manager(
                null, null, null, null,
                Rand.Next(10, 350), Rand.Next(450), Rand.Next(20, 50)
            ));
        }

        Loaded += LoadHandler;
    }

    private void LoadHandler(object sender, RoutedEventArgs e) {
        _firstThread = new Thread(StartFirstThread);
        _secondThread = new Thread(StartSecondThread);

        _firstThread.Start();
        _secondThread.Start();
    }

    private void StartFirstThread() {
        try {
            Monitor.Enter(Object);
            Monitor.PulseAll(Object);

            Dispatcher.Invoke(() => ActiveThread.Text = "Активный поток: 1");

            foreach (var seller in SellersList) {
                seller.Move();
            }
        }
        catch (Exception exception) {
            Dispatcher.Invoke(() => MessageBox.Show("Ошибка: " + exception.Message));
        }
        finally {
            Monitor.Exit(Object);
            Paint();
            Thread.Sleep(100);
            StartFirstThread();
        }
    }

    private void StartSecondThread() {
        try {
            Monitor.Enter(Object);
            Monitor.PulseAll(Object);

            Dispatcher.Invoke(() => ActiveThread.Text = "Активный поток: 2");

            foreach (var manager in ManagersList) {
                manager.Move();
            }
        }
        catch (Exception exception) {
            Dispatcher.Invoke(() => MessageBox.Show("Ошибка: " + exception.Message));
        }
        finally {
            Monitor.Exit(Object);
            Paint();
            Thread.Sleep(100);
            StartSecondThread();
        }
    }

    private void Paint() {
        try {
            Dispatcher.Invoke(() => {
                FirstCanvas.Children.Clear();
                SecondCanvas.Children.Clear();
            });

            foreach (var item in SellersList) {
                Dispatcher.Invoke(() => {
                    var image = new Image();

                    var bitmap = new BitmapImage();

                    image.Width = 100;
                    bitmap.BeginInit();
                    bitmap.UriSource = new Uri(item.ImagePath);
                    bitmap.EndInit();
                    image.Source = bitmap;

                    FirstCanvas.Children.Add(image);
                    Canvas.SetTop(image, item.Y);
                    Canvas.SetLeft(image, item.X);
                });
            }

            foreach (var item in ManagersList) {
                Dispatcher.Invoke(() => {
                    var image = new Image();

                    var bitmap = new BitmapImage();

                    image.Width = 100;
                    bitmap.BeginInit();
                    bitmap.UriSource = new Uri(item.ImagePath);
                    bitmap.EndInit();
                    image.Source = bitmap;

                    SecondCanvas.Children.Add(image);
                    Canvas.SetTop(image, item.Y);
                    Canvas.SetLeft(image, item.X);
                });
            }
        }
        catch (Exception exception) {
            MessageBox.Show("Ошибка: " + exception.Message);
        }
    }

    private void Start(object sender, RoutedEventArgs e) {
        _started = true;
    }

    private void Stop(object sender, RoutedEventArgs e) {
        new Thread(() => {
            _started = false;
            Monitor.Enter(Object);
            Monitor.PulseAll(Object);

            Dispatcher.Invoke(() => ActiveThread.Text = "Потоки на паузе");

            while (!_started) { }

            Monitor.Exit(Object);
        }).Start();
    }

    private void Confirm(object sender, RoutedEventArgs e) {
        try {
            var firstPriority = int.Parse(FirstThreadPriority.Text);
            var secondPriority = int.Parse(SecondThreadPriority.Text);

            _firstThread.Priority = (ThreadPriority)firstPriority;
            _secondThread.Priority = (ThreadPriority)secondPriority;

        }
        catch (Exception exception) {
            MessageBox.Show("Ошибка при установке приоритетов: " + exception.Message);

        }
    }
}
