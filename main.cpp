#include <iostream>
#include <vector>
#include <random>
#include <numeric>


namespace
{
   // randomness init
   std::random_device rd;
   std::mt19937 mtRand(rd());
   std::uniform_real_distribution<float> dis(0.0f, 1.0f);
}


class Entry
{
public:
   Entry(const std::string& value)
      : value(value)
   {}

   std::string value;
};

Entry pickRandomEntry(const std::vector<Entry>& entries, const std::vector<uint32_t>& weights)
{
   uint32_t totalWeight = 0;
   for (size_t i = 0; i < entries.size(); i++)
   {
      uint32_t entryWeight = weights.size() > i ? weights[i] : 0;
      totalWeight += entryWeight;
   }

   auto randomValue = dis(mtRand);

   uint32_t accumulatedWeight = 0;
   for (size_t i = 0; i < entries.size(); i++)
   {
      uint32_t entryWeight = weights.size() > i ? weights[i] : 0;
      accumulatedWeight += entryWeight;

      if (static_cast<float>(accumulatedWeight) / static_cast<float>(totalWeight) > randomValue)
      {
         return entries[i];
      }
   }

   // we shouldn't get here, but process this case anyway
   return entries.back();
}

void weightedPick()
{
   std::vector<Entry> entries{ std::string("A"), std::string("B"), std::string("C") };
   std::vector<uint32_t> weights0{ 4, 1, 3 };
   std::vector<uint32_t> weights1{ 4, 3 };
   std::vector<uint32_t> weights2{ 4, 1, 3, 7 };

   for (int i = 0; i < 100; i++)
   {
      auto entry = pickRandomEntry(entries, weights0);
      std::cout << entry.value;
   }
   std::cout << std::endl;
   for (int i = 0; i < 100; i++)
   {
      auto entry = pickRandomEntry(entries, weights1);
      std::cout << entry.value;
   }
   std::cout << std::endl;
   for (int i = 0; i < 100; i++)
   {
      auto entry = pickRandomEntry(entries, weights2);
      std::cout << entry.value;
   }
   std::cout << std::endl;
}

int32_t reverseInt(int32_t value)
{
   int32_t newValue = 0;

   while (value > 0)
   {
      if (std::numeric_limits<int32_t>::max() / (float)newValue < 10.0f)
      {
         return 0;
      }

      newValue = newValue * 10;

      int32_t digit = value % 10;
      value = value / 10;

      newValue += digit;
   }

   if (newValue > std::numeric_limits<int32_t>::max())
   {
      return 0;
   }

   return newValue;
}

void reverseInt()
{
   int32_t a = 1234350;
   int32_t b = 1102103426;

   int32_t c = reverseInt(a);
   int32_t d = reverseInt(b);

   std::cout << a << " -> " << c << std::endl;
   std::cout << b << " -> " << d << std::endl;
}

int main()
{
   std::cout << "===== reverse Int task =====" << std::endl;
   reverseInt();

   std::cout << "===== random pick task =====" << std::endl;
   weightedPick();
   return 0;
}
